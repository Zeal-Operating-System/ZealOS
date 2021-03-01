#include "C:/Home/Net/Net.HH"

#include "C:/Home/Net/NetLog"

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

#include "C:/Home/Net/NetHandler" // needs IPV4, UDP, ICMP

NetConfigure;

if (Fs != zenith_task)
{
	if (ipv4_globals.local_ip != 0) // is set if NetConfigure is successful
	{
		NetRep;

		"\nNow run one of the $MA,"Tests",LM="Cd(\"C:/Home/Net/Tests\");Dir;\n"$.\n";

		"\nIf a test crashes to Debug, try typing $FG,0$G2;$FG$\n\n";
	}
	else
	{
		"\nNetConfigure unsuccessful. See Network Log for details.\n\n";
	}

}
