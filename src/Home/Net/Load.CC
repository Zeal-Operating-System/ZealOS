Cd(__DIR__);
#include "Utilities/Net.HH"

#include "Utilities/NetLog"

#include "Utilities/NetQueue"

#include "Drivers/Run"

#include "Protocols/Ethernet"

#include "Protocols/ARP"
#include "Protocols/IPV4"
#include "Protocols/ICMP"

#include "Protocols/Sockets"

#include "Utilities/BST"

// todo create MakeUDP and MakeTCP to clean this up
#include "Protocols/UDP/UDP.HH"
#include "Protocols/UDP/UDPTree"
#include "Protocols/UDP/UDP.CC"

#include "Protocols/TCP/TCP.HH"
#include "Protocols/TCP/TCPTree"
#include "Protocols/TCP/TCP.CC"
#include "Protocols/TCP/TCPHandler"


#include "Protocols/DNS"
#include "Protocols/DHCP"

#include "Utilities/NetHandler" // needs IPV4, UDP, ICMP