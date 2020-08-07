#include "C:/Home/Net/Net.HH"

#include "C:/Home/Net/NetQueue"
#include "C:/Home/Net/PCNet"
#include "C:/Home/Net/Ethernet"

#include "C:/Home/Net/ARP"
#include "C:/Home/Net/IPV4"
#include "C:/Home/Net/ICMP"

#include "C:/Home/Net/Sockets"

#include "C:/Home/Net/UDP"

#include "C:/Home/Net/DNS"
#include "C:/Home/Net/DHCP"

#include "C:/Home/Net/NetHandlerTask" // needs IPV4, UDP, ICMP



XTalk(Fs, "NetConfigure;\n");

XTalk(Fs, "Host(\"zenithos.org\");\n");

XTalk(Fs, "DNSRep;\n");

XTalk(Fs, "ARPRep;\n");
