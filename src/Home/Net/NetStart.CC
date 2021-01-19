if (Fs != zenith_task)
{
	WinVert(2, zenith_task->win_bottom + zenith_task->win_bottom / 3, zenith_task);
	WinVert(zenith_task->win_bottom + 3, TEXT_ROWS - 2);
}
else
{
	WinVert(2, zenith_task->win_bottom + zenith_task->win_bottom / 3, zenith_task);
	WinVert(zenith_task->win_bottom + 3, TEXT_ROWS - 2, zenith_task->next_task);
}

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

if (Fs != zenith_task)
{
	NetConfigure;

	"\nNow run one of the $MA,"Tests",LM="Cd(\"C:/Home/Net/Tests\");Dir;\n"$.\n\n";
}
else
{
	XTalkStr(zenith_task->next_task, "NetConfigure;\n");
}