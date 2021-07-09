//Generic Networking definitions

#define ETHERNET_MIN_FRAME_SIZE		46
#define ETHERNET_MAC_HEADER_LENGTH	14
#define ETHERNET_ETHERTYPE_OFFSET	12
#define ETHERNET_DATA_OFFSET		14
#define MAC_ADDRESS_LENGTH			6

/*	Ethernet Frame Size.
	Linux uses 1544, OSDev and Shrine use 1548. Based on IEEE 802.3as, max frame size was agreed upon as 2000 bytes. */
#define ETHERNET_FRAME_SIZE	2000

#define HTYPE_ETHERNET	1
#define HLEN_ETHERNET	6
#define PLEN_IPV4		4

#define ETHERTYPE_IPV4	0x0800
#define ETHERTYPE_ARP	0x0806
#define ETHERTYPE_IPV6	0x86DD

#define IP_ADDRESS_LENGTH	4

/*	PCNet reroutes PCI interrupts to software. See $LK,"PCNet",A="FF:C:/Home/Net/PCNet.CC,I_PCNET0"$.
	Net Handler interrupt is generated whenever an entry is
	pushed to the NetQueue. See $LK,"NetHandler",A="FF:C:/Home/Net/NetHandler.CC,I_NETHANDLER"$.

	TODO: Make a function to auto-allocate these;
		  See note above $LK+PU,"I_USER",A="MN:I_USER"$. */

#define I_PCNET0		I_USER + 0
#define I_PCNET1		I_USER + 1
#define I_PCNET2		I_USER + 2
#define I_PCNET3		I_USER + 3

#define I_E1000_0		I_USER + 0
#define I_E1000_1		I_USER + 1
#define I_E1000_2		I_USER + 2
#define I_E1000_3		I_USER + 3

#define I_NETHANDLER	I_USER + 4

#define INT_DEST_CPU	0
